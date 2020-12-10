import React from 'react';

import {
  Button, Form, FormGroup, FormControl, ControlLabel, ButtonToolbar,
  Schema, Panel, Content, FlexboxGrid,
} from 'rsuite';

const { StringType } = Schema.Types;

const model = Schema.Model({
  name: StringType().isRequired('이름이 없습니다'),
  password: StringType().isRequired('비밀번호가 없습니다'),
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

class SignInForm extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      formValue: {
        name: '',
        password: '',
      },
      action: 'Login',
    };
    this.handleSubmit = this.handleSubmit.bind(this);
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

  render() {
    const { formValue } = this.state;

    return (
      <Content>
        <FlexboxGrid justify="end">
          <FlexboxGrid.Item>
            <Panel header={<h3>로그인</h3>} bordered >
              <Form
                ref={ref => (this.form = ref)}
                onChange={formValue => {
                  this.setState({ formValue });
                }}
                formValue={formValue}
                model={model}
              >
                <TextField name="name" label="이름" />

                <TextField name="password" label="비밀번호" type="password" />


                <ButtonToolbar>
                  <Button appearance="primary" onClick={this.handleSubmit}>
                    로그인
                  </Button>
                  <Button appearance="link" href='/signUp'>회원이 아닌가요?</Button>
                </ButtonToolbar>
              </Form>
            </Panel>
          </FlexboxGrid.Item>
        </FlexboxGrid>
      </Content>
    );
  }
}

export default SignInForm;
