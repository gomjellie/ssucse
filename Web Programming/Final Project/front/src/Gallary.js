import React from 'react';

import { Panel, FlexboxGrid } from 'rsuite';

const Card = () => (
  <Panel shaded bordered bodyFill>
    <img src="https://via.placeholder.com/240x240" style={{ width: 240 }}/>
    <Panel header="사진이름">
      <p>
        <small>A suite of React components, sensible UI design, and a friendly development experience.</small>
      </p>
    </Panel>
  </Panel>
);

class Gallary extends React.Component {
  constructor(props) {
    super(props);
  }

  render() {
    return (
      <div>
        <FlexboxGrid justify='space-between'>
          <FlexboxGrid.Item colspan={8}><Card /></FlexboxGrid.Item>
          <FlexboxGrid.Item colspan={8}>
            <Card />
          </FlexboxGrid.Item>
          <FlexboxGrid.Item colspan={8}>
            <Card />
          </FlexboxGrid.Item>
          <FlexboxGrid.Item colspan={8}>
            <Card />
          </FlexboxGrid.Item>
          <FlexboxGrid.Item colspan={8}>
            <Card />
          </FlexboxGrid.Item>
          <FlexboxGrid.Item colspan={8}>
            <Card />
          </FlexboxGrid.Item>
          <FlexboxGrid.Item colspan={8}>
            <Card />
          </FlexboxGrid.Item>
          <FlexboxGrid.Item colspan={8}>
            <Card />
          </FlexboxGrid.Item>
          <FlexboxGrid.Item colspan={8}>
            <Card />
          </FlexboxGrid.Item>
        </FlexboxGrid>
      </div>
    )
  }
};

export default Gallary;

