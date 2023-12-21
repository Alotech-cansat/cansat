import requests

class DistressCall:
    
    def __init__(self, id:int, secret_key: str, call_cordinates:str, details:str):
        self.id = id
        self.secret_key = secret_key
        self.call_cordinates = call_cordinates
        self.details = details

    @classmethod
    def from_json(cls,json) -> bool:
        obj = cls.__new__(cls)
        obj.id = json['id']
        obj.call_cordinates = json['call_cordinates']
        obj.secret_key = json['secret_key']
        obj.details = json['details']

        return obj

    def __repr__(self):
        return f'''id: {self.id},\ncall_cordinates: {self.call_cordinates},\ndetails: {self.details}
        '''


BASE_URL = "http://127.0.0.1:8000"

def get_by_id(id:int):
    res = requests.get(BASE_URL + f"/get_by_id/{id}")
    return DistressCall.from_json(res.json())

def get_by_secret_key(secret_key: str):

    res = requests.get(BASE_URL + f"/get_by_secret_key/{secret_key}")
    return DistressCall.from_json(res.json())

def new_distress_call(cordinates:str, details:str):
    pass

def delete(secret_key:str):
    pass

def update(secret_key:str, cordinates:str, details:str):
    pass