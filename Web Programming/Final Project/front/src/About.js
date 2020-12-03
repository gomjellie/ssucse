import React from 'react';

import { Placeholder, Panel } from 'rsuite';

const { Paragraph } = Placeholder;

const Article = () => (
  <Panel header={<h3>소개 페이지</h3>} bordered >
    <p>별 나는 둘 계십니다. 봄이 계집애들의 하나에 그리고 잠, 이름과, 버리었습니다.</p>
    <Paragraph style={{ marginTop: 30 }} />
    <hr />
    <p>별을 겨울이 하나에 책상을 것은 까닭입니다. 자랑처럼 동경과 풀이 북간도에 아름다운 피어나듯이 봄이 버리었습니다. 이름과, 이웃 마디씩 속의 나는 이름자 있습니다.</p>
    <Paragraph style={{ marginTop: 30 }} graph="circle" />
    <Paragraph style={{ marginTop: 30 }} graph="square" />
    <Paragraph style={{ marginTop: 30 }} graph="image" />
    <hr />
    <p>흙으로 부끄러운 헤일 가을로 다 까닭이요, 오면 헤는 지나고 봅니다. 추억과 이국 마리아 가을 까닭입니다. 잠, 써 별 가을로 별빛이 하나에 있습니다. 소학교 언덕 멀듯이, 풀이 보고, 있습니다.</p>
    <Paragraph style={{ marginTop: 30 }} rows={5} graph="image" active />
  </Panel>
);

export default Article;
