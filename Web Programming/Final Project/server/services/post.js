
const { HttpError } = require('http-errors');
const Post = require('../schemas/post');

async function createPost (newPost) {
  const {title, content, hashTag, writerName, writerEmail} = newPost;
  
  if (!title || !content || !hashTag || !writerName || !writerEmail)
    throw new Error("newPost Must have title, content, hashTag property");

  const user = await Post.create(signUpUser);

  return user;
}

module.exports = { createPost };
