var express = require('express');
var router = express.Router();
var Auth = require('../services/auth');
var jwt = require('jsonwebtoken');
var passport = require('passport');

const isNotLoggedIn = (req, res, next) => {
  if (!req.isAuthenticated()) {
    next();
  }
  res.status(500).json({
    code: 500,
    message: 'youre already logged in',
  });
}

router.post('/signUp', async function(req, res) {
  try {
    const user = await Auth.signUp(req.body);
    const accessToken = jwt.sign({ sub: user._id }, process.env.COOKIE_SECRET, { expiresIn: "30d" });

    res.status(200).json({
      accessToken,
      tokenType: "Bearer",
      user: {
        id: user._id,
        name: user.name,
        email: user.email,
      },
    });
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
    return req.login(user, (loginError) => {
      console.log('login success');
      if (loginError) {
        console.error(loginError);
        return next(loginError);
      }
      return res.status(200).json({
        message: 'login success',
      });
    });
  })(req, res, next);
  // try {
  //   const user = await Auth.signIn(req.body);
  //   const accessToken = jwt.sign({ sub: user._id }, process.env.COOKIE_SECRET, { expiresIn: "30d" });
    
  //   console.log('accessToken', accessToken);
  //   res.status(200).json({
  //     accessToken,
  //     tokenType: "Bearer",
  //     user: {
  //       id: user._id,
  //       name: user.name,
  //       email: user.email
  //     },
  //   });
  // } catch (error) {
  //   res.status(404).json({
  //     message: error.message,
  //   });
  // }
});

module.exports = router;
