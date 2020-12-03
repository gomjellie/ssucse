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
  name: StringType().isRequired('This field is required.'),
  password: StringType().isRequired('This field is required.'),
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
      formError: {},
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
    const { formError, formValue } = this.state;

    return (
      <Content>
        <FlexboxGrid justify="end">
          <FlexboxGrid.Item>
            {/* <JSONView formValue={formValue} formError={formError} /> */}
            <Panel header={<h3>Login</h3>} bordered >
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
                <TextField name="name" label="Name" />

                <TextField name="password" label="Password" type="password" />


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
