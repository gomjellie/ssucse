import React from 'react';

// import './App.css';
import 'rsuite/dist/styles/rsuite-dark.css';

import {
  Container, Header, Content, Footer, Navbar, FlexboxGrid, Panel,
  Row, Col,
} from 'rsuite';

import CheckForm from './Login';

class App extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      username: null
    };
  }

  componentDidMount() {
    fetch('http://localhost:5000/users/')
      .then(res=>res.json())
      .then(data=>this.setState({username: data.username}));
  }

  render() {
    // const { username } = this.state;
    const username = "asdf";

    return (
      <div className="App">
        <Container>
          <Header>
            <Navbar appearance="inverse">
              <Navbar.Header>
                <Row>
                  <Col xs={10}></Col>
                  <Col xs={2}>
                    <h2>Login</h2>
                  </Col>
                </Row>
              </Navbar.Header>
            </Navbar>
          </Header>
          <Content>
            <CheckForm />
          </Content>
          <Footer>Footer</Footer>
        </Container>
      </div>
    )
  }
}

export default App;
