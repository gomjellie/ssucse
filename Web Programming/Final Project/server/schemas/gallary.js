const mongoose = require('mongoose');

const { Schema } = mongoose;

const gallarySchema = new Schema({
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
    type: [String],
    required: false,
  },
  fileName: {
    type: String,
    required: true,
  },
  createdAt: {
    type: Date,
    default: Date.now,
  },
});

gallarySchema.virtual('id').get(function () {
  return this._id;
});

module.exports = mongoose.model('Gallary', gallarySchema);
