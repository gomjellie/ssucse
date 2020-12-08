import React from 'react';

import { Panel, FlexboxGrid } from 'rsuite';

const Card = ({pic}) => (
  <Panel shaded bordered bodyFill>
    <img src={`http://localhost:8000/api/static/${pic.name}`} style={{ width: 240 }} />
    <Panel header={pic.title}>
      <p>
        <small>속에서 속에 따뜻한 그들의 보배를 모래뿐일 보라. 찾아 내려온 모래뿐일 웅대한 피고, 보내는 갑 과실이 길을 것이다. 따뜻한 피고, 인류의 인간이 부패뿐이다.</small>
        <br />
        <small>
          <a>{`${pic.writer}`}</a>
          {` - ${pic.date.substr(0, 10)}`}
        </small>
      </p>
    </Panel>
  </Panel>
);

class Gallary extends React.Component {
  constructor(props) {
    super(props);
  }

  render() {
    const { pics } = this.props;
    return (
      <div>
        <FlexboxGrid justify='space-between'>
          {
            pics.map(pic => (
              <FlexboxGrid.Item colspan={8}>
                <Card pic={pic}/>
              </FlexboxGrid.Item>
            ))
          }
        </FlexboxGrid>
      </div>
    )
  }
};

export default Gallary;

