
/* 1. 부산에 사는 모든 학생들의 학번과 이름을 출력하시오 (5) */
select student_id, student_name from Student where home_address='부산';

/* 2. 학생 상담을 맡고 있지 않은 교수의 이름과 학과이름을 출력하시오 (5) */
select professor_name, dept_name from Professor where professor_id not in (select professor_id from Advisor);

/* 3. 전체 교수들의 평균 연봉보다 높은(초과) 교수의 이름, 학과이름, 연봉을 출력하시오 (5)*/
select professor_name, dept_name, salary from Professor where salary > (select avg(salary) from Professor);

/* 4. 학생들 중 F학점을 받은 학생의 이름과 총이수학점을 출력하시오 (10) */

INSERT INTO `Takes` VALUES ('20160519','MD201','가','Spring','2019','F'), ('20160519','MD303','가','Fall','2019','A');

select student_name, sum(CASE WHEN grade = 'F' THEN 0 ELSE credit END) from Student natural join Takes join Course using(course_id) GROUP BY student_id having max(grade)='F';

/* 5. 성이 김씨인 학생의 이름, 학번, 총이수학점을 출력하시오 (5) */

select student_name, student_id, sum(CASE WHEN grade = 'F' THEN 0 ELSE credit END) from Student left join Takes using(student_id) left join Course using(course_id) where student_name LIKE '김%' GROUP BY student_id;

/* 6. 학과별 학생들의 평균이수학점을 출력하시오(학과이름도 출력되어야함) (5) */

select dept_name, sum(CASE WHEN grade = 'F' THEN 0 ELSE credit END) / count(distinct student_id) from Student left join  Department using(dept_name) left join Takes using(student_id) left join (select course_id, credit from Course) as Course using(course_id) GROUP BY dept_name;

/* 7. 전체 학생의 평균이수학점보다 같거나 높은 학생들의 학번, 이름, 소속학과이름, 총이수학점을 출력하시오. (10) */

select student_id, student_name, dept_name, sum(CASE WHEN grade = 'F' THEN 0 ELSE credit END) from Student natural join Takes natural join Course GROUP BY student_id having sum(CASE WHEN grade = 'F' THEN 0 ELSE credit END) > (select sum(CASE WHEN grade = 'F' THEN 0 ELSE credit END) / count(distinct student_id) from Student left join  Department using(dept_name) left join Takes using(student_id) left join (select course_id, credit from Course) as Course using(course_id));

/* 8. 학과 예산이 가장 많은 학과에 소속된 모든 학생들의 이름을 출력하시오. (5) */

select student_name from Student natural join Department where budget=(select max(budget) from Department);

/* 9. 전체 학생들 중 서울에 살고 있고 지도교수가 있는 학생의 학번, 이름, 총이수학점, 소속학과이름, 지도교수이름을 출력하시오. (10) */

select student_id, student_name, `sum(CASE WHEN grade = 'F' THEN 0 ELSE credit END)`,  dept_name, professor_name 
from (
    select student_id, student_name, Student.dept_name, sum(CASE WHEN grade = 'F' THEN 0 ELSE credit END) 
    from Student left join Takes using(student_id) left join Course using(course_id)
    where home_address="서울" GROUP BY student_id
) as S natural join Advisor natural join Professor;

/* 10. 2018년도 가을학기에 컴퓨터학부 소속 교수들 중 성이 박씨인 교수가 가르친 교과목의 이름, 해당 수업에서의 그 학생이 받은 성적을 출력하시오. */

INSERT INTO `Teaches` VALUES ('CS1002','CS303','가','Fall','2019');
select title, grade from (select * from Teaches where professor_id = 'CS1002') as T natural inner join Takes left join Course using(course_id);

/* 11. 알고리즘 교과목을 수강하기 위해 선수강이 되어야 하는 과목의 이름을 출력하시오. (출력 시 중복 제거, 재귀적 질의 추천) (10) */

select distinct title from (
with recursive rcs(course_id, prereq_id) as (
    select course_id, prereq_id 
    from Prereq
    where course_id in (select course_id from Course where title='알고리즘')
    union all 
    select r.course_id, r.prereq_id 
    from Prereq r
    inner join rcs
        on r.course_id = rcs.prereq_id
) select * from rcs
) as R join Course on prereq_id=Course.course_id;

/* 12. 교수들의 연봉에서 7,000만원보다 적은(미만) 교수는 연봉을 5% 인상, 그렇지 않은 교수들의 연봉은 3% 인하되도록 변경하시오. (10) */

update Professor set salary = case when salary < 70 then salary * 1.05 else salary * 0.97 end;

/* 13. 2020년 기준 입학한지 4년이 넘은(초과) 학생들은 삭제하시오. (10) */

delete from Student where timestampdiff(year, admission_date, now()) > 4;
