import requests

r = requests.get("https://raw.githubusercontent.com/PA0DEV/7_Segment_Clock/7cd281ff75800fd96a23fabe00cac83e16a6d96e/scripts/latest.version?token=AV5RLCXF4WCRWE22UAEZDFDBMRKZ2")

print(r.text)
