import React from 'react';

import { Panel, Input, Alert, Divider } from 'rsuite';
import DynamicTag from './DynamicTag';

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
    this.setState({ writer: query });
  }

  onSubmit() {
    const { writer } = this.state;
    return fetch(`api/post/search?` + new URLSearchParams({
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
        if (res.posts.length === 0) {
          Alert.info("검색 결과가 없습니다");
        }
        this.setState({ posts: res.posts });
      });
  }

  render() {
    const { posts } = this.state;

    return (
      <div>
        <Panel style={{ width: 550 }} header={<h3>포스트 작성자 검색</h3>} bordered >
          <Input type="search"  onPressEnter={this.onSubmit} onChange={this.onChange} placeholder="글 작성자" />

        </Panel>
        <div style={{ width: 550, paddingTop: 30 }}>
          {posts.map((post, index) => (
            <Panel key={index} header={`${post.title} - ${post.writerName} - ${post.createdAt.substr(0, 10)}`} collapsible bordered>
              {post.content}
              <Divider />
              <DynamicTag tags={post.hashTag} />
            </Panel>
          ))}
        </div>
      </div>
    )
  }
};

export default SearchPostWriter;