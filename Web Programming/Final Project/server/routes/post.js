var express = require('express');
var router = express.Router();
var Post = require('../services/post');
var jwt = require('jsonwebtoken');
var passport = require('passport');

var { isLoggedIn } = require('../middlewares/sessionChecker');

router.post('/writePost', isLoggedIn, async function(req, res, next) {
  let reqPost = req.body.json();
  
  const {name, email} = req.session.passport;
  console.log(reqPost);
  
  
  Post.createPost({
    title: reqPost.title,
    content: reqPost.content,
    hashTag: reqPost.hashTag,
    writerName: name,
    writerEmail: email,
  });
  res.json({
    message: 'hello',
  });
});

module.exports = router;
