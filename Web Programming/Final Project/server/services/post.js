const Post = require('../schemas/post');

async function createPost (newPost) {
  const {title, content, hashTag, writerName, writerEmail} = newPost;
  
  if (title === undefined
    || content === undefined
    || writerName === undefined || writerEmail === undefined)
    throw new Error("newPost Must have title, content property");

  const user = await Post.create(newPost);

  return user;
}

async function readPostList () {
  const posts = await Post.find();

  if (posts.n === 0) {
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

async function searchWriter (writerName) {
  const res = await Post.find({
    "writerName": {"$regex": writerName},
  },
  { '_id': 0, '__v': 0 });

  return res;
}

async function searchContent (content) {
  const res = await Post.find({
    "content": {"$regex": content},
  }, 
  { '_id': 0, '__v': 0 });

  return res;
}

async function searchHashTag (hashTags) {
  const res = await Post.find({
    hashTag: {"$in" : hashTags},
  },
  { '_id': 0, '__v': 0 });

  return res;
}

module.exports = {
  createPost, readPostList, deletePost, updatePost,
  searchWriter, searchContent, searchHashTag
};

