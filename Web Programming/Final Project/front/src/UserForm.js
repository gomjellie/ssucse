import React from 'react';

import {
  Button, Form, FormGroup, FormControl, ControlLabel, ButtonToolbar,
  Schema, Panel, Row, Col, Content, FlexboxGrid,
} from 'rsuite';

import Loadable from 'react-loadable';
const { StringType, NumberType } = Schema.Types;

function MyLoader() {
  return <div>loading...</div>;
}

const JSONTree = Loadable({
  loader: () => import('react-json-tree'),
  loading: MyLoader,
});

const JSONView = ({ formValue, formError }) => (
  <Row style={{ marginBottom: 10 }}>
    <Col md={12}>
      <Panel className="json-tree-wrapper" header={<p>formValue</p>}>
        <JSONTree data={formValue} />
      </Panel>
    </Col>

    <Col md={12}>
      <Panel className="json-tree-wrapper" header={<p>formError</p>}>
        <JSONTree data={formError} />
      </Panel>
    </Col>
  </Row>
);

const model = Schema.Model({
  name: StringType().isRequired('이름이 없습니다'),
  email: StringType()
    .isEmail('유효한 이메일을 입력해주세요')
    .isRequired('이메일이 없습니다'),
  password: StringType().isRequired('비밀번호가 없습니다'),
  verifyPassword: StringType()
    .addRule((value, data) => {
      console.log(data);

      if (value !== data.password) {
        return false;
      }

      return true;
    }, '비밀번호가 일치하지 않습니다.')
    .isRequired('비밀번호를 재입력해주세요')
});

class TextField extends React.PureComponent {
  render() {
    const { name, label, accepter, ...props } = this.props;
    return (
      <FormGroup>
        <ControlLabel>{label} </ControlLabel>
        <FormControl name={name} accepter={accepter} {...props} />
      </FormGroup>
    );
  }
}

class UserForm extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      formValue: {
        name: '',
        email: '',
        password: '',
        verifyPassword: ''
      },
      formError: {},
      action: 'Login',
    };
    this.handleSubmit = this.handleSubmit.bind(this);
    this.handleCheckEmail = this.handleCheckEmail.bind(this);
  }
  handleSubmit() {
    const { formValue } = this.state;
    const { onSubmit } = this.props;
    if (!this.form.check()) {
      console.error('Form Error');
      return;
    }
    console.log(formValue, 'Form Value');
    onSubmit(formValue);
  }

  handleCheckEmail() {
    
  }
  render() {
    const { formError, formValue } = this.state;

    return (
      <Content>
        <FlexboxGrid justify="end">
          <FlexboxGrid.Item>
            {/* <JSONView formValue={formValue} formError={formError} /> */}
            <Panel header={<h3>회원가입</h3>} bordered >
              <Form
                ref={ref => (this.form = ref)}
                onChange={formValue => {
                  this.setState({ formValue });
                }}
                onCheck={formError => {
                  this.setState({ formError });
                }}
                formValue={formValue}
                model={model}
              >
                <TextField name="name" label="이름" />

                <TextField name="email" label="이메일 주소" />
                <TextField name="password" label="비밀번호" type="password" />

                <TextField name="verifyPassword" label="비밀번호 다시입력" type="password" />

                <ButtonToolbar>
                  <Button appearance="primary" onClick={this.handleSubmit}>회원가입</Button>

                </ButtonToolbar>
              </Form>
            </Panel>
          </FlexboxGrid.Item>
        </FlexboxGrid>
      </Content>
    );
  }
}

export default UserForm;
