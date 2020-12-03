var express = require('express');
var passport = require('passport');

var router = express.Router();

const isAuthenticated = function(req, res, next) {
  console.log(JSON.stringify(req.headers));
  console.log(req.session);
  if (req.isAuthenticated())
    return next();
  else {
    res.status(401).json({
      code: 401,
      message: 'failed authentication',
    });
  }
};

router.get('/', isAuthenticated, async (req, res) => {
  console.log("req.session", req.session);
  res.status(200).json({
    code: 200,
    message: 'you can access here',
  });
})

module.exports = router;
