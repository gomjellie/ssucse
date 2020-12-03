var express = require('express');
var appRoot = require('app-root-path');

var router = express.Router();

router.get('/', async (req, res) => {
    res.send(express.static(`${appRoot}/../front/build/index.html`));
});

module.exports = router;
