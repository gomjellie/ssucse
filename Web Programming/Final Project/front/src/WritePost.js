import React from 'react';

import { Panel, Input } from 'rsuite';

const WritePost = ({ onTitleChange, onContentChange, onHashTagChange }) => (
  <Panel header={<h3>새 글작성</h3>} bordered >
    <Input style={{ width: 500 }} placeholder="제목" onChange={onTitleChange} />
    <hr />
    <Input
      componentClass="textarea"
      rows={3}
      style={{ width: 500, height: 1000 }}
      placeholder="내용을 작성해주세요"
      size="lg"
      onChange={onContentChange}
    />
    <hr />
    <Input style={{ width: 500 }} placeholder="해쉬태그" onChange={onHashTagChange} />
  </Panel>
);

export default WritePost;
