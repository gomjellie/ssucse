var express = require('express');
var router = express.Router();
var Auth = require('../services/auth');
var jwt = require('jsonwebtoken');
var passport = require('passport');

var { isLoggedIn } = require('../middlewares/sessionChecker');

router.post('/signUp', async function(req, res) {
  try {
    const user = await Auth.signUp(req.body);
    
    res.redirect('/users/signIn');
  } catch (error) {
    res.status(404).json({
      message: error.message,
    });
  }
});

router.post('/signIn', async function(req, res, next) {
  passport.authenticate('local', (authError, user, info) => {
    if (authError) {
      console.error(authError);
      return next(authError);
    }
    if (!user) {
      return res.redirect('/loginError');
    }
    console.log('user', user);
    return req.login(user, (loginError) => {
      console.log('login success');
      if (loginError) {
        console.error(loginError);
        return next(loginError);
      }
      return res.status(200).json({
        message: 'login success',
        username: user.name,
      });
    });
  })(req, res, next);
});

router.get('/info', async function(req, res, next) {
  console.log('/info ', req.session);
  if (!req.isAuthenticated()) {
    return res.status(401).json({
      username: 'Guest',
    });
  }
  res.status(200).json({
    username: req.session.passport.user.name,
  });
});

router.get('/signOut', isLoggedIn, (req, res, next) => {
  console.log('/signOut isAuthenticated?: ', req.isAuthenticated());
  req.logout();
  req.session.destroy();
  res.json({
    message: '로그아웃 성공',
  });
});

module.exports = router;
