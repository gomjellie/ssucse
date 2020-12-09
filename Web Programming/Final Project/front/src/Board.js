import React from 'react';

import { PanelGroup, Panel, Divider, FlexboxGrid, Button, Modal, Input } from 'rsuite';
import DynamicTag from './DynamicTag';

class Board extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      show: false,
      content: "",
      post: {},
    };
    this.close = this.close.bind(this);
    this.open = this.open.bind(this);
    this.onContentChange = this.onContentChange.bind(this);
  }

  onContentChange(value) {
    this.setState({ content: value });
  }

  close() {
    this.setState({ show: false });
  }

  open(post) {
    this.setState({ show: true, post });
  }

  render() {
    const { posts, onPostEdit, onPostDelete, getPosts, name } = this.props;

    return (
      <div>
        <PanelGroup>
          <div style={{ width: 500 }}>
            {posts.map((post, index) => (
              <Panel key={index} header={`${post.title} - ${post.writerName} - ${post.createdAt.substr(0, 10)}`} collapsible bordered>
                {post.content}
                <Divider />
                <DynamicTag tags={post.hashTag} />
                {
                  name == post.writerName &&
                  <FlexboxGrid justify="end">
                    <FlexboxGrid.Item>
                      <Button size="xs" appearance="link" active onClick={() => this.open(post)}>수정하기</Button>
                      <Divider vertical />
                      <Button size="xs" appearance="link" active onClick={() => onPostDelete(post._id).then(getPosts)}>삭제하기</Button>
                    </FlexboxGrid.Item>

                  </FlexboxGrid>
                }
              </Panel>
            ))}
          </div>
        </PanelGroup>
        <Modal show={this.state.show} onHide={this.close}>
          <Modal.Header>
            <Modal.Title>{this.state.post.title}</Modal.Title>
          </Modal.Header>
          <Modal.Body>
            <Input onChange={this.onContentChange} name="content" rows={5} componentClass="textarea">
              {this.state.post.content}
            </Input>
          </Modal.Body>
          <Modal.Footer>
            <Button onClick={() => {
              onPostEdit(this.state.post._id, this.state.content).then(getPosts);
              this.close();
            }} appearance="primary">수정하기</Button>
            <Button onClick={this.close} appearance="subtle">취소</Button>
          </Modal.Footer>
        </Modal>
      </div>
    )
  }
};

export default Board;
