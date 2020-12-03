import React from 'react';

// import './App.css';
import 'rsuite/dist/styles/rsuite-dark.css';

import {
  Container, Header, Navbar,
  Row, Col, Sidebar, Sidenav, Icon, Dropdown, Nav,
} from 'rsuite';

import {
  BrowserRouter as Router,
  Switch,
  Route,
  Link
} from "react-router-dom";

import UserForm from './UserForm';

const NavToggle = ({ expand, onChange }) => {
  return (
    <Navbar appearance="subtle" className="nav-toggle">
      <Navbar.Body>
        <Nav>
          <Dropdown
            placement="topStart"
            trigger="click"
            renderTitle={children => {
              return <Icon style={iconStyles} icon="cog" />;
            }}
          >

            <Dropdown.Item>Sign out</Dropdown.Item>
          </Dropdown>
        </Nav>

        <Nav pullRight>
          <Nav.Item onClick={onChange} style={{ width: 56, textAlign: 'center' }}>
            <Icon icon={expand ? 'angle-left' : 'angle-right'} />
          </Nav.Item>
        </Nav>
      </Navbar.Body>
    </Navbar>
  );
};

class App extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      expand: true,
      name: 'Guest',
      accessToken: '',
    };
    this.handleToggle = this.handleToggle.bind(this);
  }

  handleToggle() {
    this.setState({
      expand: !this.state.expand,
    });
  }

  componentDidMount() {
    // fetch('http://localhost:5000/users/')
    //   .then(res => res.json())
    //   .then(data => this.setState({ username: data.username }));
  }

  async onSubmit(action, formValue) {
    await fetch(`http://localhost:5000/users/${action}`, {
      method: 'POST',
      mode: 'cors',
      // credentials: "include",
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify(formValue),
    })
      .then(res => res.json())
      .then(data => this.setState({accessToken: data.accessToken}));
      // .then(data => this.setState({ name: data.user.name }));
    
    await fetch('http://localhost:5000/test', {
      // credentials: "include",
      headers: {
        origin: 'http://localhost:5000',
        
      }
    })
      .then(console.log);
  
  }

  render() {
    const { expand, name } = this.state;

    return (
      <div className="App">
        <Router>
          <Container>
            <Sidebar
              style={{ display: 'flex', flexDirection: 'column' }}
              width={expand ? 260 : 56}
              collapsible
            >
              <Sidenav.Header>
                <div style={headerStyles}>
                  <Icon icon="logo-analytics" size="lg" style={{ verticalAlign: 0 }} />
                  <span style={{ marginLeft: 12 }}> {name} </span>
                </div>
              </Sidenav.Header>
              <Sidenav
                expanded={expand}
                defaultOpenKeys={['3']}
                appearance="subtle"
              >
                <Sidenav.Body>
                  <Nav>
                    <Nav.Item eventKey="1" icon={<Icon icon="group" />}>
                      소개 페이지
                    </Nav.Item>
                    <Nav.Item eventKey="2" active icon={<Icon icon="dashboard" />}>
                      게시판
                    </Nav.Item>
                    <Nav.Item eventKey="3" icon={<Icon icon="magic" />}>
                      갤러리
                    </Nav.Item>
                  </Nav>
                </Sidenav.Body>
              </Sidenav>
              <NavToggle expand={expand} onChange={this.handleToggle} />
            </Sidebar>
            <Switch>
              {/* <Route path="/about">
              <About />
            </Route> */}
              <Route path="/signUp">
                <UserForm onSubmit={(data) => this.onSubmit('signUp', data)} />
              </Route>
              <Route path="/">
                <UserForm onSubmit={(data) => this.onSubmit('signIn', data)} />
              </Route>
            </Switch>
          </Container>
        </Router>
      </div>
    )
  }
}

const headerStyles = {
  padding: 18,
  fontSize: 16,
  height: 56,
  background: '#34c3ff',
  color: ' #fff',
  whiteSpace: 'nowrap',
  overflow: 'hidden'
};

const iconStyles = {
  width: 56,
  height: 56,
  lineHeight: '56px',
  textAlign: 'center'
};

export default App;
