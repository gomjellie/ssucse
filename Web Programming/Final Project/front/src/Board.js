import React from 'react';

import { PanelGroup, Panel, Divider, FlexboxGrid, Button, Modal } from 'rsuite';

const Board = ({ posts, onPostEdit, onPostDelete }) => {
  const onPost = () => () => onPostEdit(post._id, post.content);

  return (
    <PanelGroup>
      <div style={{ width: 500 }}>
        {posts.map((post, index) => (
          <Panel header={`${post.title} - ${post.writerName} - ${post.createdAt.substr(0, 10)}`} collapsible bordered>
            {post.content}
            <Divider />
            <FlexboxGrid justify="end">
              <FlexboxGrid.Item>
                <Button size="xs" appearance="link" active onClick={onPost}>수정하기</Button>
                <Divider vertical />
                <Button size="xs" appearance="link" active onClick={() => onPostDelete(post._id)}>삭제하기</Button>
              </FlexboxGrid.Item>
            </FlexboxGrid>
          </Panel>
        ))}
      </div>
    </PanelGroup>
  );
}

export default Board;
