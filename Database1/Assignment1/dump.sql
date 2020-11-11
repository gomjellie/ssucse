-- MySQL dump 10.13  Distrib 8.0.22, for osx10.15 (x86_64)
--
-- Host: localhost    Database: DB20150318
-- ------------------------------------------------------
-- Server version	8.0.22

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Advisor`
--

DROP TABLE IF EXISTS `Advisor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Advisor` (
  `student_id` varchar(8) NOT NULL,
  `professor_id` varchar(8) NOT NULL,
  PRIMARY KEY (`student_id`,`professor_id`),
  KEY `professor_id_idx` (`professor_id`),
  KEY `student_id_idx` (`student_id`),
  CONSTRAINT `advisor_ibfk_1` FOREIGN KEY (`professor_id`) REFERENCES `Professor` (`professor_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `advisor_ibfk_2` FOREIGN KEY (`student_id`) REFERENCES `Student` (`student_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Advisor`
--

LOCK TABLES `Advisor` WRITE;
/*!40000 ALTER TABLE `Advisor` DISABLE KEYS */;
/*!40000 ALTER TABLE `Advisor` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Course`
--

DROP TABLE IF EXISTS `Course`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Course` (
  `course_id` varchar(8) NOT NULL,
  `title` varchar(32) DEFAULT NULL,
  `dept_name` varchar(128) DEFAULT NULL,
  `credit` int DEFAULT NULL,
  PRIMARY KEY (`course_id`),
  KEY `dept_name_idx` (`dept_name`),
  CONSTRAINT `course_ibfk_1` FOREIGN KEY (`dept_name`) REFERENCES `Department` (`dept_name`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `course_chk_1` CHECK (((`credit` >= 0) and (`credit` <= 3)))
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Course`
--

LOCK TABLES `Course` WRITE;
/*!40000 ALTER TABLE `Course` DISABLE KEYS */;
INSERT INTO `Course` VALUES ('CS101','프로그래밍','컴퓨터학부',1),('CS201','자료구조','컴퓨터학부',3),('CS202','알고리즘','컴퓨터학부',3),('CS203','파일처리','컴퓨터학부',3),('CS204','리눅스시스템프로그래밍','컴퓨터학부',3),('CS301','운영체제','컴퓨터학부',3),('CS302','정보보안','컴퓨터학부',3),('CS303','데이터베이스','컴퓨터학부',3),('MD101','프로그래밍','미디어학부',2),('MD201','자료구조','미디어학부',3),('MD202','알고리즘','미디어학부',3),('MD204','리눅스시스템프로그래밍','미디어학부',3),('MD301','운영체제','미디어학부',3),('MD303','데이터베이스','미디어학부',3),('SW101','프로그래밍','소프트웨어학부',3),('SW201','자료구조','소프트웨어학부',3),('SW202','알고리즘','소프트웨어학부',3),('SW204','리눅스시스템프로그래밍','소프트웨어학부',3),('SW301','운영체제','소프트웨어학부',3),('SW303','데이터베이스','소프트웨어학부',3);
/*!40000 ALTER TABLE `Course` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Department`
--

DROP TABLE IF EXISTS `Department`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Department` (
  `dept_name` varchar(128) NOT NULL,
  `budget` int DEFAULT NULL,
  PRIMARY KEY (`dept_name`),
  CONSTRAINT `department_chk_1` CHECK (((`budget` >= 150) and (`budget` <= 300))),
  CONSTRAINT `department_chk_2` CHECK ((`dept_name` in (_utf8mb4'컴퓨터학부',_utf8mb4'미디어학부',_utf8mb4'소프트웨어학부')))
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Department`
--

LOCK TABLES `Department` WRITE;
/*!40000 ALTER TABLE `Department` DISABLE KEYS */;
INSERT INTO `Department` VALUES ('미디어학부',300),('소프트웨어학부',150),('컴퓨터학부',150);
/*!40000 ALTER TABLE `Department` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Prereq`
--

DROP TABLE IF EXISTS `Prereq`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Prereq` (
  `course_id` varchar(8) NOT NULL,
  `prereq_id` varchar(8) NOT NULL,
  PRIMARY KEY (`course_id`,`prereq_id`),
  KEY `prereq_id` (`prereq_id`),
  CONSTRAINT `prereq_ibfk_1` FOREIGN KEY (`course_id`) REFERENCES `Course` (`course_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `prereq_ibfk_2` FOREIGN KEY (`prereq_id`) REFERENCES `Course` (`course_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Prereq`
--

LOCK TABLES `Prereq` WRITE;
/*!40000 ALTER TABLE `Prereq` DISABLE KEYS */;
INSERT INTO `Prereq` VALUES ('CS201','CS101'),('CS202','CS201'),('MD201','MD101'),('MD202','MD201'),('SW201','SW101'),('SW202','SW201');
/*!40000 ALTER TABLE `Prereq` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Professor`
--

DROP TABLE IF EXISTS `Professor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Professor` (
  `professor_id` varchar(8) NOT NULL,
  `professor_name` char(24) DEFAULT NULL,
  `dept_name` varchar(128) DEFAULT NULL,
  `salary` int DEFAULT NULL,
  `start_date` date DEFAULT NULL,
  PRIMARY KEY (`professor_id`),
  KEY `professor_ibfk_idx` (`dept_name`),
  CONSTRAINT `professor_ibfk` FOREIGN KEY (`dept_name`) REFERENCES `Department` (`dept_name`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `professor_chk_1` CHECK (((`salary` >= 50) and (`salary` <= 100)))
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Professor`
--

LOCK TABLES `Professor` WRITE;
/*!40000 ALTER TABLE `Professor` DISABLE KEYS */;
INSERT INTO `Professor` VALUES ('CS1000','홍지만','컴퓨터학부',100,'2000-03-01'),('CS1001','최봉준','컴퓨터학부',90,'2019-03-01'),('CS1002','박동주','컴퓨터학부',80,'2000-03-01'),('CS1003','유재우','컴퓨터학부',70,'1990-03-01'),('CS1004','김병기','컴퓨터학부',50,'1990-03-01'),('MD1000','최형일','미디어학부',100,'2000-03-01'),('MD1001','박재완','미디어학부',90,'2000-03-01'),('MD1002','윤준성','미디어학부',80,'2000-03-01'),('MD1003','정기철','미디어학부',70,'2000-03-01'),('MD1004','김규정','미디어학부',50,'2010-03-01'),('SW1000','이상호','소프트웨어학부',100,'2000-03-01'),('SW1001','김수동','소프트웨어학부',90,'2000-03-01'),('SW1002','박광영','소프트웨어학부',80,'2000-03-01'),('SW1003','김명호','소프트웨어학부',70,'2000-03-01'),('SW1004','서창진','소프트웨어학부',50,'2000-03-01');
/*!40000 ALTER TABLE `Professor` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Section`
--

DROP TABLE IF EXISTS `Section`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Section` (
  `section_id` varchar(8) NOT NULL,
  `course_id` varchar(8) NOT NULL,
  `semester` char(24) NOT NULL,
  `year` varchar(4) NOT NULL,
  PRIMARY KEY (`section_id`,`course_id`,`semester`,`year`),
  KEY `course_id_idx` (`course_id`),
  KEY `course_rfed_idx_1` (`semester`),
  KEY `course_rfed_idx_2` (`year`),
  CONSTRAINT `section_ibfk_1` FOREIGN KEY (`course_id`) REFERENCES `Course` (`course_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `section_chk_1` CHECK ((`semester` in (_utf8mb4'Spring',_utf8mb4'Fall')))
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Section`
--

LOCK TABLES `Section` WRITE;
/*!40000 ALTER TABLE `Section` DISABLE KEYS */;
INSERT INTO `Section` VALUES ('가','CS101','Spring','2018'),('가','CS201','Spring','2018'),('가','CS202','Fall','2018'),('가','CS203','Spring','2018'),('가','CS204','Spring','2018'),('가','CS301','Fall','2018'),('가','CS302','Fall','2018'),('가','CS303','Spring','2018'),('나','CS301','Fall','2018'),('나','CS303','Spring','2018'),('가','CS101','Spring','2019'),('가','CS201','Spring','2019'),('가','CS202','Fall','2019'),('가','CS203','Spring','2019'),('가','CS204','Spring','2019'),('가','CS301','Fall','2019'),('가','CS302','Fall','2019'),('가','CS303','Spring','2019'),('가','MD101','Spring','2019'),('가','MD201','Spring','2019'),('가','MD202','Fall','2019'),('가','MD204','Spring','2019'),('가','MD301','Fall','2019'),('가','MD303','Spring','2019'),('가','SW101','Spring','2019'),('가','SW201','Spring','2019'),('가','SW202','Fall','2019'),('가','SW204','Spring','2019'),('가','SW301','Fall','2019'),('가','SW303','Spring','2019'),('나','CS301','Fall','2019'),('나','CS303','Spring','2019'),('나','MD301','Fall','2019'),('나','MD303','Spring','2019'),('나','SW301','Fall','2019'),('나','SW303','Spring','2019'),('가','CS201','Spring','2020'),('가','MD201','Spring','2020'),('가','SW201','Spring','2020');
/*!40000 ALTER TABLE `Section` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Student`
--

DROP TABLE IF EXISTS `Student`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Student` (
  `student_id` varchar(8) NOT NULL,
  `student_name` char(24) DEFAULT NULL,
  `dept_name` varchar(128) DEFAULT NULL,
  `admission_date` date DEFAULT NULL,
  `home_address` varchar(256) DEFAULT NULL,
  PRIMARY KEY (`student_id`),
  KEY `student_ibfk_1_idx` (`dept_name`),
  CONSTRAINT `student_ibfk_1` FOREIGN KEY (`dept_name`) REFERENCES `Department` (`dept_name`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Student`
--

LOCK TABLES `Student` WRITE;
/*!40000 ALTER TABLE `Student` DISABLE KEYS */;
/*!40000 ALTER TABLE `Student` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Takes`
--

DROP TABLE IF EXISTS `Takes`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Takes` (
  `student_id` varchar(8) NOT NULL,
  `course_id` varchar(8) NOT NULL,
  `section_id` varchar(8) NOT NULL,
  `semester` char(24) NOT NULL,
  `year` varchar(4) NOT NULL,
  `grade` char(4) DEFAULT NULL,
  PRIMARY KEY (`student_id`,`year`,`semester`,`section_id`,`course_id`),
  KEY `takes_ibfk_2_idx` (`course_id`),
  KEY `takes_ibfk_3_idx` (`section_id`),
  KEY `takes_ibfk_4_idx` (`semester`),
  KEY `takes_ibfk_5_idx` (`year`),
  CONSTRAINT `takes_ibfk_1` FOREIGN KEY (`student_id`) REFERENCES `Student` (`student_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `takes_ibfk_2` FOREIGN KEY (`course_id`) REFERENCES `Section` (`course_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `takes_ibfk_3` FOREIGN KEY (`section_id`) REFERENCES `Section` (`section_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `takes_ibfk_4` FOREIGN KEY (`semester`) REFERENCES `Section` (`semester`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `takes_ibfk_5` FOREIGN KEY (`year`) REFERENCES `Section` (`year`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Takes`
--

LOCK TABLES `Takes` WRITE;
/*!40000 ALTER TABLE `Takes` DISABLE KEYS */;
/*!40000 ALTER TABLE `Takes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Teaches`
--

DROP TABLE IF EXISTS `Teaches`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `Teaches` (
  `professor_id` varchar(8) NOT NULL,
  `course_id` varchar(8) NOT NULL,
  `section_id` varchar(8) NOT NULL,
  `semester` char(24) NOT NULL,
  `year` varchar(4) NOT NULL,
  PRIMARY KEY (`professor_id`,`course_id`,`section_id`,`semester`,`year`),
  KEY `teaches_ibfk_2_idx` (`course_id`),
  KEY `teaches_ibfk_3_idx` (`section_id`),
  KEY `teaches_ibfk_4_idx` (`semester`),
  KEY `teaches_ibfk_5_idx` (`year`),
  CONSTRAINT `teaches_ibfk_1` FOREIGN KEY (`professor_id`) REFERENCES `Professor` (`professor_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `teaches_ibfk_2` FOREIGN KEY (`course_id`) REFERENCES `Section` (`course_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `teaches_ibfk_3` FOREIGN KEY (`section_id`) REFERENCES `Section` (`section_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `teaches_ibfk_4` FOREIGN KEY (`semester`) REFERENCES `Section` (`semester`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `teaches_ibfk_5` FOREIGN KEY (`year`) REFERENCES `Section` (`year`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Teaches`
--

LOCK TABLES `Teaches` WRITE;
/*!40000 ALTER TABLE `Teaches` DISABLE KEYS */;
/*!40000 ALTER TABLE `Teaches` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2020-11-11 20:58:10
