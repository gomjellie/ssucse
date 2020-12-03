var express = require('express');
var router = express.Router();
var Auth = require('../services/auth');
var jwt = require('jsonwebtoken');

router.post('/signUp', async function(req, res) {
  try {
    const user = await Auth.signUp(req.body);
    const accessToken = jwt.sign({ sub: user._id }, process.env.JWT_SECRET, { expiresIn: "30d" });

    res.status(200).json({
      accessToken,
      tokenType: "Bearer",
      user: {
        id: user._id,
        name: user.name,
        email: user.email,
      },
    });
  } catch (error) {
    res.status(404).json({
      message: error.message,
    });
  }
});

router.post('/signIn', async function(req, res) {
  try {
    const user = await Auth.signIn(req.body);
    const accessToken = jwt.sign({ sub: user._id }, process.env.JWT_SECRET, { expiresIn: "30d" });

    res.status(200).json({
      accessToken,
      tokenType: "Bearer",
      user: {
        id: user._id,
        name: user.name,
        email: user.email
      },
    });
  } catch (error) {
    res.status(404).json({
      message: error.message,
    });
  }
});

module.exports = router;
