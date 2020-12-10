import React from 'react';

import { Panel, Input, Button, ButtonToolbar, Uploader } from 'rsuite';
import DynamicTag from './DynamicTag';

class WriteImage extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      title: "",
      files: [],
      hashTag: [],
    };
    this.handleTitleChange = this.handleTitleChange.bind(this);
    this.handleFileChange = this.handleFileChange.bind(this);
    this.handleSubmitPost = this.handleSubmitPost.bind(this);
    this.handleHashTagChange = this.handleHashTagChange.bind(this);
  }

  handleHashTagChange(newTags) {
    this.setState({ hashTag: newTags });
  }

  handleFileChange(files) {
    this.setState({ files });
  }

  handleTitleChange(title) {
    this.setState({ title });
  }

  handleSubmitPost() {
    const {title, files, hashTag} = this.state;
    fetch("http://localhost:8000/api/gallary/new", {
      method: 'POST',
      mode: 'cors',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({title, files, hashTag}),
    });
  }

  render() {
    return (
      <Panel header={<h3>사진 업로드하기</h3>} bordered >
        <Input style={{ width: 500 }} placeholder="제목" onChange={this.handleTitleChange} />
        <hr />
        <Uploader
          style={{ width: 500 }}
          listType="picture-text"
          action="http://localhost:8000/api/gallary/img"
          draggable
          fileList={this.state.files}
          onChange={this.handleFileChange}
          name='img'
          withCredentials
          multiple={false}
          renderFileInfo={(file, fileElement) => {
            return (
              <div>
                <span>File Name: {file.name}</span>
                <p>File URL: {file.url}</p>
              </div>
            );
          }}
        >
          <div style={{ lineHeight: '200px' }}>클릭하거나 파일을 여기로 드래그하세요</div>
        </Uploader>
        <br />
        {/* <Input style={{ width: 500 }} placeholder="해쉬태그" onChange={onHashTagChange} /> */}
        <DynamicTag onTagChange={this.handleHashTagChange} editable />
        <hr />
        <ButtonToolbar>
          <Button appearance="primary" onClick={this.handleSubmitPost}>글쓰기</Button>
        </ButtonToolbar>
      </Panel>
    )
  }
};

export default WriteImage;
