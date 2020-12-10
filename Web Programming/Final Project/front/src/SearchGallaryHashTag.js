import React from 'react';

import { Panel, Input, Alert, Divider } from 'rsuite';
import Gallary from './Gallary';

class SearchGallaryHashTag extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      hashTag: '',
      pics: [],
    };

    this.onChange = this.onChange.bind(this);
    this.onSubmit = this.onSubmit.bind(this);
  }

  onChange(query, event) {
    this.setState({ hashTag: query });
  }

  onSubmit() {
    const { hashTag } = this.state;
    return fetch("http://localhost:8000/api/gallary/search?" + new URLSearchParams({
      hashTag,
    }))
      .then(res => {
        if (!res.ok) {
          Alert.error("검색 실패!");
          throw new Error("검색 실패");
        }
        return res.json();
      })
      .then(res => {
        if (res.pics.length === 0) {
          Alert.info("검색 결과가 없습니다");
        }
        this.setState({ pics: res.pics });
      });
  }

  render() {
    const { pics } = this.state;

    return (
      <div style={{ width: '50vw' }}>
        <Panel header={<h3>갤러리 해쉬태그 검색</h3>} bordered bodyFill>
          <Input type="search"  onPressEnter={this.onSubmit} onChange={this.onChange} placeholder="해쉬태그" />

        </Panel>
        <Gallary style={{ paddingTop: 30 }} pics={pics} user="guest" />
      </div>
    )
  }
};

export default SearchGallaryHashTag;
