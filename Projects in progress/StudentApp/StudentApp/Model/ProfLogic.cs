using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StudentApp.Model
{
    class ProfLogic
    {
        private dbPELEntities studentDb = new dbPELEntities();

        public List<ProfModel> GetProfModels()
        {
            var profQuery = (from professor in studentDb.Professors
                                where professor.Active == true
                                select new ProfModel
                                {
                                    Id = (int)professor.ProfessorId,
                                    Nume = (string)professor.LastName,
                                    Prenume = (string)professor.FirstName,
                                    Telefon = (string)professor.Telephone,                               
                                    CNP = (string)professor.Cnp
                                }).ToList();

            return profQuery;
        }
    }
}
