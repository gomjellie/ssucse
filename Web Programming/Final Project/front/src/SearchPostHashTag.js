import React from 'react';

import { Panel, Input } from 'rsuite';
class SearchPostHashTag extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
    };
  }

  render() {
    return (
      <Panel header={<h3>포스트 해쉬태그 검색</h3>} bordered >
        <Input style={{ width: 500 }} placeholder="해쉬태그" />
        
      </Panel>
    )
  }
};

export default SearchPostHashTag;
