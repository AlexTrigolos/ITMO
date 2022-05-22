import { ApiProperty } from '@nestjs/swagger';
import { ValidateIf } from 'class-validator';

export class DeleteMyPostDto {
  @ApiProperty()
  @ValidateIf((object, value) => value !== undefined)
  id: number;
}
