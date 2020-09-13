delete from mysiteapp_actormodel;
delete from mysiteapp_moviemodel;
delete from mysiteapp_commentmodel;
delete from mysiteapp_moviemodel_actors;
update sqlite_sequence SET seq = 0 where name = 'mysiteapp_actormodel';
update sqlite_sequence SET seq = 0 where name = 'mysiteapp_moviemodel';
update sqlite_sequence SET seq = 0 where name = 'mysiteapp_commentmodel';
