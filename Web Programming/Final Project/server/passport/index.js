const passport = require('passport');
const JwtStrategy = require('passport-jwt').Strategy;
const LocalStrategy = require('passport-local').Strategy;
const { ExtractJwt } = require('passport-jwt');

// const kakao = require('./kakaoStrategy');
const { User } = require('../schemas/user');

passport.use(new JwtStrategy({
  jwtFromRequest: ExtractJwt.fromAuthHeaderAsBearerToken('authorization'),
  secretOrKey: process.env.JWT_SECRET,
}, async (payload, done) => {
  try {
    const user = await User.findOne({_id: payload.sub});

    if (!user) {
      return done(null, false);
    }

    done(null, user);
  } catch (error) {
    done(error, false);
  }
}
));

passport.serializeUser((user, done) => {
  console.log('serializeUser', user);
  done(null, user);
});

passport.deserializeUser((user, done) => {
  console.log('deserializeUser', user);
  done(null, user);
});
