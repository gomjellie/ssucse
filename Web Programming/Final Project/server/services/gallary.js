const Gallary = require('../schemas/gallary');

async function create (newPic) {
  const {title, fileName, writerName, writerEmail} = newPic;
  
  if (title === undefined
    || fileName === undefined
    || writerName === undefined || writerEmail === undefined)
    throw new Error("newPic Must have title, fileName property");

  const user = await Gallary.create(newPic);

  return user;
}

async function getList () {
  const pics = await Gallary.find();

  if (pics.n === 0) {
    throw new Error("Post.find() returned empty result");
  }

  return pics;
}

async function deletePic (_id) {
  const res = await Gallary.deleteOne({_id});

  return res;
}

async function updatePic (id, content) {
  // 구현 안할것임
//   const res = await Post.updateOne({_id: id}, {content});

//   return res;
}

async function searchHashTag (hashTags) {
  const res = await Gallary.find({
    hashTag: {"$in" : hashTags},
  },
  { '_id': 0, '__v': 0 });

  return res;
}

module.exports = { create, getList, deletePic, updatePic, searchHashTag };

