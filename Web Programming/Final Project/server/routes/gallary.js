var express = require('express');
var router = express.Router();
var path = require('path');
var multer = require('multer');
var fs = require('fs');
var Gallary = require('../services/gallary');

var { isLoggedIn } = require('../middlewares/sessionChecker');

try {
  fs.readdirSync('uploads');
} catch (error) {
  console.error('uploads 폴더가 없어 uploads  폴더를 생성합니다');
  fs.mkdirSync('uploads');
}

const upload = multer({
  storage: multer.diskStorage({
    destination(req, file, cb) {
      cb(null, 'uploads/');
    },
    filename(req, file, cb) {
      const ext = path.extname(file.originalname);
      cb(null, path.basename(file.originalname, ext) + ext); // 파일이름 충돌 고려하지않음.
    },
  }),
  limits: { fileSize: 20 * 1024 * 1024 },
});

router.post('/img', isLoggedIn, upload.single('img'), async (req, res) => {
  console.log(req.file);
  res.json({ url: `/img/${req.file.filename}` });
});

router.post('/new', isLoggedIn, async (req, res) => {
  const { name, email } = req.session.passport.user;
  const { files, title, hashTag } = req.body;

  files.forEach(async file => {
    await Gallary.create({
      fileName: file.name,
      title: title,
      writerName: name,
      writerEmail: email,
      hashTag,
    });
  });

  res.json({
    body: req.body,
  });
});

router.get('/list', async (req, res) => {
  const pics = await Gallary.getList();

  // const reduced = pics.reduce((acc, pic) => {
  //   acc.push({
  //     name: pic.fileName,
  //     title: pic.title,
  //     writer: pic.writerName,
  //     date: pic.createdAt,
  //     hashTag: pic.hashTag,
  //     id: pic._id,
  //   });
  //   return acc;
  // }, []);

  res.json({
    pics,
  });
});

router.delete('/:id', isLoggedIn, async (req, res) => {
  const id = req.params.id;

  const success = Gallary.deletePic(id);

  if (!success) {
    res.status(404).json({
      message: `id: ${id}에 해당하는 사진을 못 찾았습니다.`,
    });
  }

  res.json({
    message: '삭제 성공',
  });
});

router.get('/search', isLoggedIn, async (req, res, next) => {
  const {hashTag} = req.query;

  if (hashTag !== undefined) {
    const pics = await Gallary.searchHashTag(hashTag);

    res.json({
      pics,
    });
    return;
  }

  res.status(400).json({
    message: "hashTag 필드를 받지 못했습니다",
  });
});

module.exports = router;
