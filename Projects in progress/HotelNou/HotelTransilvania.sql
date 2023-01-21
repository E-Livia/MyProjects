create table Angajati(

id_angajat integer identity(1,1) primary key,
nume_angajat varchar(50),
CNP integer,
nr_telefon integer,
adresa_email varchar(50),
data_angajarii date,
username varchar(50),
parola varchar(50),
rol bit
)

alter table Angajati
alter column CNP bigint

insert into Angajati values('Mihnea Iulian',5010804272834,0724354765,'miulian@admin.com','2014-06-02','Iulian','parola',1)
insert into Angajati values('Stefania',5010804272834,0724354765,'stef@admin.com','2014-06-02','administrator','parola',1)

create table Clienti(

id_client integer identity(1,1) primary key,
nume_client varchar(50),
nr_telefon integer,
adresa_email integer,
username varchar(50),
parola varchar(50)
)

alter table Clienti
alter column adresa_email varchar(50)

create table Tip_Camera(

id_camera integer identity(1,1) primary key,
tip_camera varchar(50),
numar_camere integer
)

create table Imagini(

id_imagine integer identity(1,1) primary key,
img_path varchar(100),
id_camera integer,
constraint fk_camera foreign key(id_camera) references Tip_Camera(id_camera)
)

create table Rezervare(

id_rezervare integer identity(1,1) primary key,
data_inceput date,
data_incheiere date,
status_rezervare varchar(50),
id_client integer,
constraint fk_client foreign key(id_client) references Clienti(id_client)
)

create table Rezervare_Camera(

id_rez_cam integer identity(1,1) primary key,
id_camera integer,
id_rezervare integer,
nr_camere integer,
constraint fk_camera1 foreign key(id_camera) references Tip_Camera(id_camera),
constraint fk_rezervare foreign key(id_rezervare) references Rezervare(id_rezervare)
)

create table Pret(

id_pret integer identity(1,1) primary key,
valoare float,
data_inceput date,
data_incheiere date,
id_camera integer,
constraint fk_camera2 foreign key(id_camera) references Tip_Camera(id_camera)
)


create table Oferte(

id_oferta integer identity(1,1) primary key,
data_inceput date,
data_incheiere date,
pret float,
id_camera integer,
constraint fk_camera3 foreign key(id_camera) references Tip_Camera(id_camera)
)

create table Dotari(

id_dotare integer identity(1,1) primary key,
denumire varchar(100)
)

create table Dotari_Camera(

id_dot_cam integer identity(1,1) primary key,
id_camera integer,
id_dotare integer,
constraint fk_camera4 foreign key(id_camera) references Tip_Camera(id_camera),
constraint fk_dotare foreign key(id_dotare) references Dotari(id_dotare)
)

create table Servicii_Suplimentare(

id_serviciu integer identity(1,1) primary key,
denumire_serviciu varchar(50),
pret float
)

create table Serviciu_Rezervare(

id_serviciu_rez integer identity(1,1) primary key,
id_serviciu integer,
id_rezervare integer,
constraint fk_serv foreign key(id_serviciu) references Servicii_Suplimentare(id_serviciu),
constraint fk_rez foreign key(id_rezervare) references Rezervare(id_rezervare)
)
