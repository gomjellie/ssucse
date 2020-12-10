import React from 'react';

import { Panel, Input } from 'rsuite';
class SearchPostWriter extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
    };
  }

  
  render() {
    return (
      <Panel header={<h3>포스트 작성자 검색</h3>} bordered >
        <Input style={{ width: 500 }} placeholder="글 작성자" />
        
      </Panel>
    )
  }
};

export default SearchPostWriter;
