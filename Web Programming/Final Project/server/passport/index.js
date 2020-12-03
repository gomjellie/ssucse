const { compare } = require('bcrypt');
const passport = require('passport');
const JwtStrategy = require('passport-jwt').Strategy;
const LocalStrategy = require('passport-local').Strategy;
const { ExtractJwt } = require('passport-jwt');

const { User } = require('../schemas/user');

passport.serializeUser((user, done) => {
  console.log('serializeUser', user);
  done(null, user);
});

passport.deserializeUser((user, done) => {
  console.log('deserializeUser', user);
  done(null, user);
});

console.log('JWT_SECRET: ', process.env.JWT_SECRET);

passport.use(new JwtStrategy({
  jwtFromRequest: ExtractJwt.fromHeader('Authorization'),
  secretOrKey: process.env.JWT_SECRET,
}, async (payload, done) => {
  try {
    console.log("!----------payload", payload, payload.sub);
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

// passport.use(new LocalStrategy({
//   usernameField: 'name',
//   passwordField: 'password',
// }, async (username, password, donc) => {
//   try {
//     console.log("!----------localstrategy");
//     const user = await User.findOneById({username})
//       .then((user) => {
//         const match = compare(password, user.password);
//         if (match)
//           return match;
//       })
//       .catch((e) => {
//         if (!user) {
//           return done(null, false);
//         }
//       })
//   } catch (error) {
//     console.log(error);
//   }
// }
// ));
