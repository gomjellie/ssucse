const mongoose = require('mongoose');
const sha256 = require("sha256");

const { Schema } = mongoose;

const userSchema = new Schema({
  email: {
    type: String,
    unique: true,
    required: true,
  },
  name: {
    type: String,
    required: true,
  },
  password: {
    type: String,
    min: 64,
    max: 64,
    required: true,
  },
  createdAt: {
    type: Date,
    default: Date.now,
  },
});

userSchema.virtual('id').get(function () {
  return this._id;
});

userSchema.set('toJSON', {
  virtuals: true,
});

userSchema.set('toObject', {
  virtuals: true,
});

userSchema.methods.hashPassword = (password) => {
  return sha256(password);
}

userSchema.methods.comparePassword = (plainPassword) => {
  const otherPassword = this.hashPassword(plainPassword);
  return otherPassword === this.password;
}

module.exports = mongoose.model('User', userSchema);
