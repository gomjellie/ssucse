import React from 'react';

import { Panel, Input, Button, ButtonToolbar, Uploader } from 'rsuite';
import DynamicTag from './DynamicTag';

const fileList = [
  {
    name: 'a.png',
    fileKey: 1,
    url:
      'https://user-images.githubusercontent.com/1203827/47638792-92414e00-db9a-11e8-89c2-f8f430a23cd3.png'
  },
  {
    name: 'b.png',
    fileKey: 2,
    url:
      'https://user-images.githubusercontent.com/1203827/47638807-9d947980-db9a-11e8-9ee5-e0cc9cd7e8ad.png'
  }
];

const WriteImage = ({ onTitleChange, onContentChange, onHashTagChange, onSubmitPost }) => (
  <Panel header={<h3>사진 업로드하기</h3>} bordered >
    <Input style={{ width: 500 }} placeholder="제목" onChange={onTitleChange} />
    <hr />
    <Uploader
      style={{ width: 500 }}
      listType="picture-text"
      action="http://localhost:8000/api/galary"
      draggable
      withCredentials
      renderFileInfo={(file, fileElement) => {
        return (
          <div>
            <span>File Name: {file.name}</span>
            <p>File URL: {file.url}</p>
          </div>
        );
      }}
    >
      <div style={{ lineHeight: '200px' }}>Click or Drag files to this area to upload</div>
    </Uploader>
    <br />
    {/* <Input style={{ width: 500 }} placeholder="해쉬태그" onChange={onHashTagChange} /> */}
    <DynamicTag />
    <hr />
    <ButtonToolbar>
      <Button appearance="primary" onClick={onSubmitPost}>글쓰기</Button>
    </ButtonToolbar>
  </Panel>
);

export default WriteImage;
