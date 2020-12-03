import React from 'react';

// import './App.css';
import 'rsuite/dist/styles/rsuite-dark.css';

import {
  Container, Header, Navbar,
  Row, Col, Sidebar, Sidenav, Icon, Dropdown, Nav,
} from 'rsuite';

import {
  Switch,
  Route,
} from "react-router-dom";

import history from './history';
import UserForm from './UserForm';
import SignInForm from './SignInForm';
import About from './About';

const NavToggle = ({ expand, onChange, onSignOut }) => {
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

            <Dropdown.Item eventKey="9" onSelect={async (eventKey) => {
              fetch('http://localhost:8000/api/users/signOut')
                .then(() => {
                  history.push('/signOut');
                  onSignOut();
                });
            }}>로그아웃</Dropdown.Item>
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
    this.onSignOut = this.onSignOut.bind(this);
  }

  onSignOut() {
    this.setState({
      name: 'Guest',
    });
  }

  handleToggle() {
    this.setState({
      expand: !this.state.expand,
    });
  }

  componentDidMount() {
    try {
      fetch('http://localhost:8000/api/users/info').then(res => res.json())
        .then(data => this.setState({ name: data.username }));
    } catch (error) {
      console.log(this.state);
      this.setState({ name: 'Guest' });
    }
  }

  async onSubmit(action, formValue) {
    await fetch(`http://localhost:8000/api/users/${action}`, {
      method: 'POST',
      mode: 'cors',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify(formValue),
    })
      .then(res => res.json())
      .then(data => {
        this.setState({ name: data.username });
        history.push('/');
      });
  }

  render() {
    const { expand, name } = this.state;

    return (
      <div className="App">
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
            <NavToggle expand={expand} onChange={this.handleToggle} onSignOut={this.onSignOut} />
          </Sidebar>
          <div style={absoluteCenterStyle}>
            <Switch>
              <Route exact path="/">
                <h2>HEAD </h2>
              </Route>
              <Route path="/about">
                <About />
              </Route>
              <Route path="/signUp">
                <UserForm onSubmit={(data) => this.onSubmit('signUp', data)} />
              </Route>
              <Route path="/signIn">
                <SignInForm onSubmit={(data) => this.onSubmit('signIn', data)} />
              </Route>
              <Route path="/signOut">
                <h2>로그아웃에 성공했습니다</h2>
              </Route>
            </Switch>
          </div>
        </Container>
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

const absoluteCenterStyle = {
  position: 'absolute', left: '50%', top: '50%',
  transform: 'translate(-50%, -50%)'
}

export default App;