import React from 'react';

import { Panel, Input } from 'rsuite';
class SearchPostContent extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
    };
  }

  
  render() {
    return (
      <Panel header={<h3>포스트 내용 검색</h3>} bordered >
        <Input style={{ width: 500 }} placeholder="글 내용" />
        
      </Panel>
    )
  }
};

export default SearchPostContent;
