import React from 'react';

import { Panel, Input, Alert } from 'rsuite';
class SearchPostWriter extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      writer: '',
      posts: [],
    };

    this.onChange = this.onChange.bind(this);
    this.onSubmit = this.onSubmit.bind(this);
  }

  onChange(query, event) {
    this.setState({writer: query});
  }

  onSubmit() {
    const {writer} = this.state;
    return fetch("http://localhost:8000/api/post/search?" + new URLSearchParams({
      writer,
    }))
      .then(res => {
        if (!res.ok) {
          Alert.error("검색 실패!");
          throw new Error("검색 실패");
        }
        return res.json();
      })
      .then(res => {
        this.setState({posts: res.posts});
      });
  }

  render() {
    return (
      <Panel header={<h3>포스트 작성자 검색</h3>} bordered >
        <Input type="search" style={{ width: 500 }} onPressEnter={this.onSubmit} onChange={this.onChange} placeholder="글 작성자" />

      </Panel>
    )
  }
};

export default SearchPostWriter;
