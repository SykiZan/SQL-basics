select * 
from students
where age between '18' and '20'
---------------------------------------------------
select * 
from students
where student_name like '%ch%' 
or student_name like '%%nd'
---------------------------------------------------
select * 
from students
where student_name like '%ae%' 
or student_name like '%ph%'
and age !=19
---------------------------------------------------


select * from students
order by age desc
limit 4
---------------------------------------------------
select * from students
where age <= 20 and student_no between '3' and '5'
or student_no = 7
or (student_no <=4)
---------------------------------------------------


select * , replace(department,substring(department from 1 for 3))
from professors
---------------------------------------------------
select last_name || '  works in the ' || department ||  ' department'
from professors
---------------------------------------------------
select 'It is ' || (salary > 95000) || ' that professor ' || last_name || ' is highly paid'
from professors
---------------------------------------------------
select max(salary),min(salary)
from professors
where last_name != 'Wilson'
---------------------------------------------------
select  substring(email, position('@' in email)+1) as domain_name,count(*)
from employees
where email is not null 
group by domain_name
order by count(*) desc
---------------------------------------------------

select gender ,region_id, min(salary),max(salary),round(avg(salary))
from employees
group by region_id,gender
order by gender
---------------------------------------------------
select state
from fruit_imports
order by supply desc
limit 1
---------------------------------------------------
select season,max(cost_per_unit)
from fruit_imports
group by season
---------------------------------------------------
select state,count(name)
from fruit_imports
group by name,state
having count(*) > 1
---------------------------------------------------
select season,count(name)
from fruit_imports
group by season
having count(name) = 3 or count(name) = 4
---------------------------------------------------

select state, max(supply * cost_per_unit)
from fruit_imports
group by state
order by max desc
limit 1
---------------------------------------------------
select *
from employees
where  department in (select department from departments where division = 'Electronics') 
------------------------------------------------------------------------------------------------
select first_name, department, (select max(salary) from employees) - salary
from employees
where region_id in(select region_id from regions where country in('Asia','Canada'))
------------------------------------------------------------------------------------------------------
select * from employees
where department in (select department from departments where division = 'Kids')
and hire_date > all(select hire_date from employees where department = 'Maintenance')
------------------------------------------------------------------------------------------------------
select max(salary )from
(select salary
from employees
group by salary
having count(salary)>1)  a
------------------------------------------------------------------------------------------------------
select round (avg(salary))
from employees
where salary not in(
select salary from employees
where salary in(select max(salary)from employees )
or salary =(select min(salary) from employees)
)
------------------------------------------------------------------------------------------------------
select student_name
from students
where student_no in(select student_no from student_enrollment
				   where course_no in
				   (select course_no from courses where course_title in ('Physics', 'US History')))

------------------------------------------------------------------------------------------------------
select student_name
from students
where student_no in(select max (count) from 
					(select count(*) from student_enrollment
				   group by student_no) a )
------------------------------------------------------------------------------------------------------				  
select student_name , age
from students
where age in (
select max(age)
from students) 
------------------------------------------------------------------------------------------------------

select category, count(category) from
(
select first_name,salary,
case
	when salary <100000 then 'Underpaid'
	when salary >100000 and salary < 160000 then 'Paid well'
	when salary > 160000 then 'Executive'
end as category
from employees
) a
group by category
------------------------------------------------------------------------------------------------------
select sum(case when department = 'Sports' then 1 else 0 end) sports_emp,
	   sum(case when department = 'Tools' then 1 else 0 end) tools_emp,
	   sum(case when department = 'Clothing' then 1 else 0 end) clothing_emp,
	   sum(case when department = 'Computers' then 1 else 0 end) computers_emp
from employees
------------------------------------------------------------------------------------------------------

select first_name,
case    when region_id = '1' then (select country from regions where region_id = '1') else null end,
case	when region_id = '2' then (select country from regions where region_id = '2') else null end,
case	when region_id = '3' then (select country from regions where region_id = '3') else null end,
case	when region_id = '4' then (select country from regions where region_id = '4') else null end,
case	when region_id = '5' then (select country from regions where region_id = '5') else null end,
case	when region_id = '6' then (select country from regions where region_id = '6') else null end,
case	when region_id = '7' then (select country from regions where region_id = '7') else null end
from employees
------------------------------------------------------------------------------------------------------
select sum(case when region_id in 
		   (select region_id from regions where country = 'United States') then 1 else 0 end) as US,
		   sum(case when region_id in 
		   (select region_id from regions where country = 'Asia') then 1 else 0 end) as Asia,
		   sum(case when region_id in 
		   (select region_id from regions where country = 'Canada') then 1 else 0 end) as Canada
from employees
------------------------------------------------------------------------------------------------------

select *,case when sum < 20000 then 'low'
 when sum > 20000 and sum < 50000 then 'enough' 
 when sum > 50000 then 'full' end from(
select name , sum(supply)
from fruit_imports
group by name
	) a
------------------------------------------------------------------------------------------------------	
select sum(case
           when season = 'Winter' then round(supply * cost_per_unit) else 0 end) winter,
		sum(case
           when season = 'Fall' then round(supply * cost_per_unit) else 0 end) fall, 
		sum(case
           when season = 'Summer' then round(supply * cost_per_unit) else 0 end) summer,
		sum(case
           when season = 'All Year' then round(supply * cost_per_unit) else 0 end) all_year,
		 sum(case
           when season = 'Spring' then round(supply * cost_per_unit) else 0 end) spring  
from fruit_imports
------------------------------------------------------------------------------------------------------
select department, count(*)
from employees
group by department
having count(*) > 38
order by count 
---------------------------------------------------
select department , (select count(*) 
					from employees e1 where e1.department = e2.department
					having count(*) > 38)
from employees e2
group by department

select department, (select max (salary) from employees where department = d.department)
from departments d
where 38 < (select count(*)
		   from employees e where e.department = d.department)
		   
------------------------------------------------------------------------------------------------------		   
		   
		   
		   
		   
		   
		   select department, (select max(salary) from employees e1
				   where e1.department = e2.department),
			   (select min(salary) from employees e1
			  where e1.department = e2.department)
from employees e2
group by department
---------------------------------------------------


select department, (select salary from employees e1
				   where e1.department = e2.department
				   and salary = (select max(salary)from employees  group by department)
				   or salary = (select min(salary)from employees  group by department))
			     
from employees e2
group by department
------------------------------------------------------------------------------------------------------

select distinct department, case when salary in 
(select max(salary) from employees e1 
 where e2.department = e1.department) then salary 
 when salary in 
(select min(salary) from employees e1 
 where e2.department = e1.department ) then salary end,
 case
 when first_name in
 (select first_name from employees e1
 where salary in (select max(salary) from employees e2 where e1.department = e2.department group by department)) 
 then first_name
 when first_name in
 (select first_name from employees e1
 where salary in (select min(salary) from employees e2 where e1.department = e2.department group by department)) 
 then first_name
 end
from employees e2
------------------------------------------------------------------------------------------------------
select distinct department ,first_name,case
           when salary in (select max(salary) from employees e1 where e1.department = e2.department) 
		   then salary 
		   when salary in (select min(salary) from employees e1 where e1.department = e2.department) 
		   then salary  end as max_min_sal,
		case
           when salary in (select max(salary) from employees e1 where e1.department = e2.department) 
		   then 'max salary'
		   when salary in (select min(salary) from employees e1 where e1.department = e2.department) 
		   then 'min salary'  end as min_max
from employees e2
where salary in (select case
           when salary in (select max(salary) from employees e1 where e1.department = e2.department) 
		   then salary 
		   when salary in (select min(salary) from employees e1 where e1.department = e2.department) 
		   then salary  end)
order by department,min_max   
-----------------------------------------------------
select first_name,email,division
from employees e, departments d
where e.department = d.department
and email is not null 
---------------------------------------------------

select country,count(*)
from regions r, employees e
where e.region_id = r.region_id
group by country
---------------------------------------------------

select distinct e.department
from employees e left join departments d
on e.department = d.department
where d.department is null
---------------------------------------------------

select department , count(*)
from employees
group by department
union all
select 'TOTAL',count(*)
from employees
---------------------------------------------------

select first_name,department,hire_date,country
from employees e inner join regions r on e.region_id  = r.region_id
where hire_date in(select max(hire_date) from employees)
or hire_date = any(select min(hire_date) from employees)
---------------------------------------------------