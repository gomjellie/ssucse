import React from 'react';

import { Panel, FlexboxGrid, Button, Divider, Alert } from 'rsuite';
import DynamicTag from './DynamicTag';

const Card = ({ pic, getPics, user }) => (
  <Panel shaded bordered bodyFill>
    <img alt="" src={`api/images/${pic.fileName}`} style={{ width: 260 }} />

    <h6 style={{ marginLeft: 12, marginTop: 8 }}>{pic.title}</h6>
    <FlexboxGrid style={{ paddingLeft: 12, paddingRight: 12 }} justify="space-between">
      <FlexboxGrid.Item>
        <small>
          <a>{`${pic.writerName}`}</a>
        </small>
      </FlexboxGrid.Item>
      <FlexboxGrid.Item>
        <small>{`${pic.createdAt.substr(0, 10)}`}</small>
      </FlexboxGrid.Item>
    </FlexboxGrid>

    <DynamicTag style={{ padding: 8 }} tags={pic.hashTag} />
    {
      user === pic.writerName &&
      <FlexboxGrid style={{ paddingBottom: 8, paddingRight: 8 }} justify="end">
        <FlexboxGrid.Item>
          <Button size="xs" appearance="link" onClick={
            () => Alert.info("구현되지 않았습니다.")
          } active>수정하기</Button>
          <Divider vertical />
          <Button size="xs" appearance="link" onClick={() => {
            fetch(`api/gallary/${pic._id}`, {
              method: 'DELETE',
            }).then(() => getPics());
          }} active>삭제하기</Button>
        </FlexboxGrid.Item>
      </FlexboxGrid>
    }
  </Panel>
);

class Gallary extends React.Component {
  constructor(props) {
    super(props);
  }

  render() {
    const { pics, getPics, user, style } = this.props;
    return (
      <div style={style}>
        <FlexboxGrid justify='space-between'>
          {
            pics.map((pic, idx) => (
              <FlexboxGrid.Item key={idx} colspan={8}>
                <Card key={pic._id} pic={pic} getPics={getPics} user={user} />
              </FlexboxGrid.Item>
            ))
          }
        </FlexboxGrid>
      </div>
    )
  }
};

export default Gallary;

