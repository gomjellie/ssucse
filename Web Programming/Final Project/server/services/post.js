const Post = require('../schemas/post');

async function createPost (newPost) {
  const {title, content, hashTag, writerName, writerEmail} = newPost;
  
  if (title === undefined
    || content === undefined
    || hashTag === undefined || writerName === undefined || writerEmail === undefined)
    throw new Error("newPost Must have title, content, hashTag property");

  const user = await Post.create(newPost);

  return user;
}

async function readPostList () {
  const posts = await Post.find();

  if (!posts) {
    throw new Error("Post.find() returned empty result");
  }

  return posts;
}

async function deletePost (_id, writerEmail) {
  const res = await Post.deleteOne({_id, writerEmail});

  return res;
}

async function updatePost (id, writerEmail, content) {
  const res = await Post.updateOne({_id: id, writerEmail}, {content});

  return res;
}

module.exports = { createPost, readPostList, deletePost, updatePost };
