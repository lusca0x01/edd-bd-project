insert into tipo_pet(codigo, descricao) values(1, 'cachorro');
insert into tipo_pet(codigo, descricao) values(2, 'gato');
insert into pessoa(codigo, nome, fone) values(1, 'joão', '859995566');
insert into pessoa(codigo, nome, fone, endereco) values(2, 'maria', '859996677', 'rua b, nr 202');
insert into pet(codigo, codigo_cli, nome, codigo_tipo) values(1, 1, 'bilu', 2);
insert into pessoa(codigo, nome, fone, data_nascimento) values(3, 'josé', '859997788', '04/10/2001');
insert into pessoa(codigo, nome, fone, data_nascimento) values(4, 'Kosé', '859997788', '04/10/2001');
insert into pessoa(codigo, nome, fone, data_nascimento) values(6, 'Aosé', '859997788', '04/10/2001');
insert into pessoa(codigo, nome, fone, data_nascimento) values(7, 'Bosé', '859997788', '04/10/2001');
insert into pet(codigo, codigo_cli, nome, codigo_tipo) values(2, 1, 'brother', 1);
insert into pet(codigo, codigo_cli, nome, codigo_tipo) values(3, 2, 'minie', 1);
select * from pet order by
