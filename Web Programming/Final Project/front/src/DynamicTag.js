import React from 'react';
import PropTypes from 'prop-types';

import { IconButton, Input, TagGroup, Tag, Icon } from 'rsuite';

class DynamicTag extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      typing: false,
      inputValue: '',
      tags: props.tags,
    };
    this.handleButtonClick = this.handleButtonClick.bind(this);
    this.handleInputChange = this.handleInputChange.bind(this);
    this.handleInputConfirm = this.handleInputConfirm.bind(this);
  }

  handleButtonClick() {
    this.setState(
      {
        typing: true
      },
      () => {
        this.input.focus();
      }
    );
  }

  handleInputChange(inputValue) {
    this.setState({ inputValue });
  }

  handleInputConfirm() {
    const { inputValue, tags } = this.state;
    const { onTagChange } = this.props;
    const nextTags = inputValue ? [...new Set([...tags, inputValue])] : tags;
    this.setState({
      tags: nextTags,
      typing: false,
      inputValue: ''
    });
    onTagChange(nextTags);
  }

  handleTagRemove(tag) {
    const { tags } = this.state;
    const { onTagChange } = this.props;

    const nextTags = tags.filter(item => item !== tag);
    this.setState({
      tags: nextTags
    });
    onTagChange(nextTags);
  }

  renderInput() {
    const { typing, inputValue } = this.state;

    if (typing) {
      return (
        <Input
          className="tag-input"
          inputRef={ref => {
            this.input = ref;
          }}
          size="xs"
          style={{ width: 70 }}
          value={inputValue}
          onChange={this.handleInputChange}
          onBlur={this.handleInputConfirm}
          onPressEnter={this.handleInputConfirm}
        />
      );
    }

    return (
      <IconButton
        className="tag-add-btn"
        onClick={this.handleButtonClick}
        icon={<Icon icon="plus" />}
        appearance="ghost"
        size="xs"
      />
    );
  }
  render() {
    let { tags } = this.state;
    if (this.props.editable === false) {
      tags = this.props.tags;
    }
    
    const { editable, style } = this.props;

    return (
      <TagGroup style={style}>
        {tags.map((item, index) => (
          <Tag
            key={`${index} ${item}`}
            closable={editable}
            onClose={() => {
              this.handleTagRemove(item);
            }}
          >
            <a>{item}</a>
          </Tag>
        ))}
        {editable && this.renderInput()}
      </TagGroup>
    );
  }
}

DynamicTag.propTypes = {
  editable: PropTypes.bool,
  onTagChange: PropTypes.func,
  tags: PropTypes.array,
}

DynamicTag.defaultProps = {
  editable: false,
  tags: [],
}

export default DynamicTag;
