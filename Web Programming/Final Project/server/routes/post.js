var express = require('express');
var router = express.Router();
var Post = require('../services/post');
var jwt = require('jsonwebtoken');
var passport = require('passport');

var { isLoggedIn } = require('../middlewares/sessionChecker');

router.post('/write', isLoggedIn, async function(req, res, next) {
  let reqPost = req.body;
  
  console.log(req.session);
  const {name, email} = req.session.passport.user;
  
  const newPost = {
    title: reqPost.title,
    content: reqPost.content,
    hashTag: reqPost.hashTag,
    writerName: name,
    writerEmail: email,
  };

  console.log(newPost);
  
  Post.createPost(newPost);
  
  res.json({
    message: 'post success',
    post: newPost,
  });
});

router.get('/list', isLoggedIn, async function(req, res, next) {
  
});

module.exports = router;
