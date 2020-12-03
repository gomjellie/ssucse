import React from 'react';

import { PanelGroup, Panel, Placeholder } from 'rsuite';

const { Paragraph } = Placeholder;

const Board = () => (
  <PanelGroup style={{width: 500}}>
    <Panel header={<h3>게시판 글1</h3>} bordered >
      <Paragraph style={{ marginTop: 30 }} />
    </Panel>
    <Panel header={<h3>게시판 글2</h3>} bordered >
      <Paragraph style={{ marginTop: 30 }} graph="circle" />
      <Paragraph style={{ marginTop: 30 }} graph="square" />
      <Paragraph style={{ marginTop: 30 }} graph="image" />
    </Panel>
    <Panel header={<h3>게시판 글2</h3>} bordered >
      <Paragraph style={{ marginTop: 30 }} rows={5} graph="image" active />
    </Panel>
    <Panel header={<h3>게시판 글1</h3>} bordered >
      <Paragraph style={{ marginTop: 30 }} />
    </Panel>
    <Panel header={<h3>게시판 글2</h3>} bordered >
      <Paragraph style={{ marginTop: 30 }} graph="circle" />
      <Paragraph style={{ marginTop: 30 }} graph="square" />
      <Paragraph style={{ marginTop: 30 }} graph="image" />
    </Panel>
    <Panel header={<h3>게시판 글2</h3>} bordered >
      <Paragraph style={{ marginTop: 30 }} rows={5} graph="image" active />
    </Panel>
  </PanelGroup>
);

export default Board;
