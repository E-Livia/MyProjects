//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated from a template.
//
//     Manual changes to this file may cause unexpected behavior in your application.
//     Manual changes to this file will be overwritten if the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace HotelNou
{
    using System;
    using System.Collections.Generic;
    
    public partial class Serviciu_Rezervare
    {
        public int id_serviciu_rez { get; set; }
        public Nullable<int> id_serviciu { get; set; }
        public Nullable<int> id_rezervare { get; set; }
    
        public virtual Rezervare Rezervare { get; set; }
        public virtual Servicii_Suplimentare Servicii_Suplimentare { get; set; }
    }
}