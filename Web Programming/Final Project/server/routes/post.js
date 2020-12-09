var express = require('express');
var router = express.Router();
var Post = require('../services/post');
var jwt = require('jsonwebtoken');
var passport = require('passport');

var { isLoggedIn } = require('../middlewares/sessionChecker');

router.post('/write', isLoggedIn, async function(req, res, next) {
  let reqPost = req.body;
  const {name, email} = req.session.passport.user;
  
  const newPost = {
    title: reqPost.title,
    content: reqPost.content,
    hashTag: reqPost.hashTag,
    writerName: name,
    writerEmail: email,
  };

  Post.createPost(newPost);
  
  res.json({
    message: 'post success',
    post: newPost,
  });
});

router.get('/list', async function(req, res, next) {
  const posts = await Post.readPostList();

  console.log(posts);
  res.json({
    posts: posts,
  });
});

router.delete('/delete/:id', isLoggedIn, async (req, res, next) => {
  const id = req.params.id;
  const {email} = req.session.passport.user;
  const success = await Post.deletePost(id, email);

  if (success.n == 0) {
    res.status(404).json({
      message: `id: ${id}에 해당하는 포스트를 발견하지 못했습니다.`,
    });
  }

  res.json({
    message: '삭제 성공',
  });
});

router.put('/update', isLoggedIn, async (req, res, next) => {
  const { id, content } = req.body;
  const {email} = req.session.passport.user;

  const success = await Post.updatePost(id, email, content);

  console.log('success: ', success);

  if (success.n == 0) {
    res.status(404).json({
      message: `id: ${id} 를 업데이트하지 못했습니다`,
    });
  }

  res.json({
    message: '업데이트 성공',
  });

});

module.exports = router;
