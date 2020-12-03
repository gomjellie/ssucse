var express = require('express');
var passport = require('passport');

var router = express.Router();

const isAuthenticated = function(req, res, next) {
  if (req.isAuthenticated())
    return next();
  res.redirect('/failed');
};

router.get('/', isAuthenticated, async (req, res) => {
  res.code(200).json({
    code: 200,
    message: 'you can access here',
  });
})

module.exports = router;
