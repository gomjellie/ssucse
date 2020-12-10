import React from 'react';

import { Panel, FlexboxGrid, Button, Divider, Alert } from 'rsuite';
import DynamicTag from './DynamicTag';

const Card = ({ pic, getPics, user }) => (
  <Panel shaded bordered bodyFill>
    <img src={`http://localhost:8000/api/images/${pic.name}`} style={{ width: 260 }} />
    <Panel header={pic.title}>
      <p>
        <small>속에서 속에 따뜻한 그들의 보배를 모래뿐일 보라. 찾아 내려온 모래뿐일 웅대한 피고, 보내는 갑 과실이 길을 것이다. 따뜻한 피고, 인류의 인간이 부패뿐이다.</small>
        <br />
        <small style={{ lineHeight: 2 }}>
          <a>{`${pic.writer}`}</a>
          {` - ${pic.date.substr(0, 10)}`}
        </small>
      </p>
      <DynamicTag tags={pic.hashTag} />
      {
        user == pic.writer &&
        <FlexboxGrid style={{ paddingTop: 10 }} justify="end">
          <FlexboxGrid.Item>
            <Button size="xs" appearance="link" onClick={
              () => Alert.info("구현되지 않았습니다.")
            } active>수정하기</Button>
            <Divider vertical />
            <Button size="xs" appearance="link" onClick={() => {
              fetch(`http://localhost:8000/api/gallary/${pic.id}`, {
                method: 'DELETE',
              }).then(() => getPics());
            }} active>삭제하기</Button>
          </FlexboxGrid.Item>
        </FlexboxGrid>
      }
    </Panel>
  </Panel>
);

class Gallary extends React.Component {
  constructor(props) {
    super(props);
  }

  render() {
    const { pics, getPics, user } = this.props;
    return (
      <div>
        <FlexboxGrid justify='space-between'>
          {
            pics.map((pic, idx) => (
              <FlexboxGrid.Item key={idx} colspan={8}>
                <Card pic={pic} getPics={getPics} user={user} />
              </FlexboxGrid.Item>
            ))
          }
        </FlexboxGrid>
      </div>
    )
  }
};

export default Gallary;

