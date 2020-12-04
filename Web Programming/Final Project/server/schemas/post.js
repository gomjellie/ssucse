const mongoose = require('mongoose');

const { Schema } = mongoose;
const { userSchema } = require('./user');

const postSchema = new Schema({
  title: {
    type: String,
    required: true,
  },
  writerName: {
    type: String,
    required: true,
  },
  writerEmail: {
    type: String,
    required: true,
  },
  hashTag: {
    type: String,
    required: false,
  },
  content: {
    type: String,
    required: true,
  },
  comment: String,
  createdAt: {
    type: Date,
    default: Date.now,
  },
});

postSchema.virtual('id').get(function () {
  return this._id;
});

module.exports = mongoose.model('Post', postSchema);
