using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StudentApp.Model
{
    class StudentLogic
    {
        private dbPELEntities studentDb = new dbPELEntities();

        public List<StudentModel> GetStudentModels()
        {
            var studentQuery = (from student in studentDb.Students
                                where student.Active == true
                                select new StudentModel
                                {
                                    Id = (int)student.StudentId,
                                    Nume = (string)student.LastName,
                                    Prenume = (string)student.FirstName,
                                    GrupaId = (int)student.GroupeId,
                                    Email = (string)student.Email,
                                    CNP = (string)student.Cnp
                                }).ToList();

            return studentQuery;
        }

        public void DeleteStudent(int id)
        {
            using (SqlConnection con = ((SqlConnection)studentDb.Database.Connection))
            {
                SqlCommand cmd = new SqlCommand("DELETEROOM", con);
                cmd.CommandType = CommandType.StoredProcedure;
                SqlParameter idFeature = new SqlParameter("@id", id);
                cmd.Parameters.Add(idFeature);
                con.Open();
                cmd.ExecuteNonQuery();
                studentDb.SaveChanges();
            }

        }
    }
}
