import React from 'react';

import { Panel, Input, Button, ButtonToolbar } from 'rsuite';

import DynamicTag from './DynamicTag';

const WritePost = ({ onTitleChange, onContentChange, onHashTagChange, onSubmitPost }) => (
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
    
    <DynamicTag style={{ width: 500 }} onTagChange={onHashTagChange} editable />
    {/* <Input style={{ width: 500 }} placeholder="해쉬태그" onChange={onHashTagChange} /> */}
    <hr />
    <ButtonToolbar>
      <Button appearance="primary" onClick={onSubmitPost}>글쓰기</Button>
    </ButtonToolbar>
  </Panel>
);

export default WritePost;
