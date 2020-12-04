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
import Board from './Board';
import WritePost from './WritePost';

const signOut = async () => {
  return new Promise((resolve, reject) => {
    fetch('http://localhost:8000/api/users/signOut')
      .then(() => {
        resolve();
      });
  });
}

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
              signOut().then(onSignOut);
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
      active: '유저관리',
      newPost: {},
    };
    this.handleToggle = this.handleToggle.bind(this);
    this.onSignOut = this.onSignOut.bind(this);
    this.handleSelect = this.handleSelect.bind(this);
    this.onTitleChange = this.onTitleChange.bind(this);
    this.onContentChange = this.onContentChange.bind(this);
    this.onHashTagChange = this.onHashTagChange.bind(this);
    this.onSubmitPost = this.onSubmitPost.bind(this);
  }

  onSubmitPost() {
    try {
      console.log(this.state.newPost);
      fetch('http://localhost:8000/api/post/write', {
        method: 'POST',
        mode: 'cors',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify(this.state.newPost),
      })
        .then(res => res.json())
        .then(console.log);
    } catch (error) {

    }
  }

  onHashTagChange(hashTag) {
    this.state.newPost.hashTag = hashTag;
  }

  onContentChange(content) {
    this.state.newPost.content = content;
  }

  onTitleChange(title) {
    this.state.newPost.title = title;
  }


  handleSelect(activeKey) {
    this.setState({ active: activeKey });
  }

  onSignOut() {
    this.setState({
      name: 'Guest',
    });
    history.push('/signOut');
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
    const { expand, name, active } = this.state;

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
                <Icon icon="linux" size="lg" style={{ verticalAlign: 0 }} />
                <span style={{ marginLeft: 15 }}> {name}님 안녕하세요 </span>
              </div>
            </Sidenav.Header>
            <Sidenav
              expanded={expand}
              defaultOpenKeys={['user', "board"]}
              appearance="subtle"
              activeKey={active}
              onSelect={this.handleSelect}
            >
              <Sidenav.Body>
                <Nav>
                  <Dropdown
                    eventKey="user"
                    trigger="hover"
                    title="유저관리"
                    icon={<Icon icon="magic" />}
                    placement="rightStart"
                  >
                    <Dropdown.Item onClick={() => history.push('/signUp')} eventKey="signUp">회원가입</Dropdown.Item>
                    <Dropdown.Item onClick={() => history.push('/signIn')} eventKey="signIn">로그인</Dropdown.Item>
                    {
                      name !== 'Guest' && <Dropdown.Item onClick={() => signOut().then(this.onSignOut)} eventKey="signOut">로그아웃</Dropdown.Item>
                    }
                  </Dropdown>
                  <Nav.Item eventKey="about" onClick={() => history.push('/about')} icon={<Icon icon="pagelines" />}>
                    소개 페이지
                  </Nav.Item>
                  <Dropdown
                    eventKey="board"
                    trigger="hover"
                    title="게시판"
                    icon={<Icon icon="frame" />}
                    placement="rightStart"
                  >
                    <Dropdown.Item onClick={() => history.push('/writePost')} eventKey="writePost">글쓰기</Dropdown.Item>
                    <Dropdown.Item onClick={() => history.push('/board')} eventKey="board">글목록</Dropdown.Item>
                  </Dropdown>
                  <Nav.Item eventKey="galary" icon={<Icon icon="image" />}>
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
                <h2>메인 페이지 입니다.</h2>
              </Route>
              <Route path="/about">
                <About />
              </Route>
              <Route path="/board">
                <Board />
              </Route>
              <Route path="/writePost">
                <WritePost
                  onTitleChange={this.onTitleChange}
                  onContentChange={this.onContentChange}
                  onHashTagChange={this.onHashTagChange}
                  onSubmitPost={this.onSubmitPost}
                />
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
  position: 'absolute', left: '50%', top: 50,
  transform: 'translate(-50%, -0%)'
}

export default App;
