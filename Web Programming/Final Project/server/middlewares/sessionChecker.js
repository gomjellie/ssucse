
const isNotLoggedIn = (req, res, next) => {
  if (!req.isAuthenticated()) {
    next();
  }
  else {
    res.status(500).json({
      code: 500,
      username: req.session.passport.name,
      message: '이미 로그인 되어있습니다.',
    });
  }
};

const isLoggedIn = (req, res, next) => {
  console.log('isLoggedIn ', req.session);
  if (req.isAuthenticated()) {
    next();
  }
  else {
    res.status(500).json({
    message: '로그인 되어있지 않습니다.',
  });
  }
};

module.exports = { isNotLoggedIn, isLoggedIn };
