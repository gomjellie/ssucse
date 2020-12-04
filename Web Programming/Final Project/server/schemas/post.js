const mongoose = require('mongoose');

const { Schema } = mongoose;
import { userSchema } from './user';

const postSchema = new Schema({
  title: {
    type: String,
    required: true,
  },
  writer: {
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

module.exports = mongoose.model('Post', postSchema);
