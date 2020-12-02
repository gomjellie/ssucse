
const { HttpError } = require('http-errors');
const sha256 = require('sha256');
const User = require('../schemas/user');

async function signUp (signUpUser) {
  const {email, name, password} = signUpUser;
  
  if (email === undefined || name === undefined || password === undefined)
    throw new Error("signUpUser Must have email, name, password property");

  signUpUser.password = sha256(password);

  const user = await User.create(signUpUser);

  return user;
}

async function signIn (signInUser) {
  const {email, name, password} = signInUser;
  
  if (email === undefined || name === undefined || password === undefined)
    throw new Error("signInUser Must have email, name, password property");

  const user = await User.findOne({email: signInUser.email, password: sha256(password)});
  if (user === null)
    throw new HttpError(404, "user not found");
  
  return user;
}

module.exports = { signUp, signIn };
